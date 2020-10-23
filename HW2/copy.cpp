#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>

int main(int argc, char* argv[])
{
        // check arguments quantity
        if(argc < 3)
        {
                std::cout << "Too few arguments\n";

                return -1;
        }

        // create file descriptors
        int source = open(argv[1], O_RDONLY);
        int destination = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP);

        // system checks
        if(source < 0)
        {
                std::cerr << "Couldn't open file\n";

                return -1;
        }

        if(destination < 0)
        {
                std::cerr << "Couldn't create file\n";

                return -1;
        }

        long null_bytes = 0, data_bytes = 0, source_logical_size = 0, source_physical_size = 0, buffer_size = 0, read_result, write_result,  hole_ptr = 0, data_ptr = 0, offset = 0, lseek_result = 0;
        char* buffer;

        while(true)
        {
                // find a hole
                data_ptr = lseek(source, offset, SEEK_HOLE);

                //adjust offset
                offset = data_ptr;

                source_logical_size += data_ptr - hole_ptr;

                buffer_size = data_ptr - hole_ptr;

                buffer = new char[buffer_size];

                // put the cursor back for read()
                lseek(source, hole_ptr - offset, SEEK_CUR);

                // read buffer
                read_result = read(source, buffer, buffer_size);

                std::cout << "read result: " << read_result << '\n';
                // check if could read
                if(read_result == -1)
                {
                        std::cerr << "Error\n";
                        return errno;
                }

                hole_ptr = lseek(source, offset, SEEK_DATA);

                // check if there is no more data is left
                if(hole_ptr == -1)
                {
                        if(errno == ENXIO)
                        {
                                hole_ptr = lseek(source, 0, SEEK_END);
                                
                                //put last holes and check if no error
                                if(lseek(destination, hole_ptr - data_ptr, SEEK_END) < 0)
                                {
                                        std::cerr << "Something went wrong\n";
                                        
                                        return errno;
                                }
                                
                                source_physical_size += hole_ptr - data_ptr;

                                break;
                        }                        
                        else
                        {
                                std::cerr << "Something went wrong\n";

                                return errno;
                        }
                }

                source_physical_size += hole_ptr - data_ptr;

                // adjust offset
                offset = hole_ptr;

                // write buffer
                write_result = write(destination, buffer, buffer_size);

                // check if could write
                if(write_result < 0)
                {
                        std::cerr << "Couldn't write\n";

                        return errno;
                }

                data_bytes += write_result;

                // put holes
                lseek_result = lseek(destination, hole_ptr - data_ptr, SEEK_END);

                // check if could put holes
                if(lseek_result < 0)
                {
                        std::cerr << "Something went wrong\n";

                        return errno;
                }

                null_bytes += hole_ptr - data_ptr;
        }

        // in some cases last data block isn't being written in destination in the main loop. This part of code is for writing the missing part
        if(errno == ENXIO)
        {
                // write buffer
                write_result = write(destination, buffer, buffer_size);

                // check if could write
                if(write_result < 0)
                {
                        std::cerr << "Couldn't write\n";

                        return errno;
                }

                data_bytes += write_result;
        }
        
        // close files
        close(destination);
        close(source;
        
        // print
        std::cout << "\nSource file\nlogical size: " << source_logical_size / 1000 << "KB\nphysical size: " << (source_logical_size + source_physical_size) / 1000 << "KB\n\n";

        std::cout << "Destination file\nlogical size: " << data_bytes / 1000 << "KB\nphysical size: " << (data_bytes + null_bytes) / 1000 << "KB\n";

        return 0;
}
