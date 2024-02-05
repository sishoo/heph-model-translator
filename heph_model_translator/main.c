
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include <sys/mman.h>
#include <sys/stat.h>

#include <unistd.h>
#include <fcntl.h>

#define PRINT_ERROR(err_msg) fprintf(stderr, "%s\n", err_msg);
#define NUM_FLAGS sizeof(FLAGS) / sizeof(char *)

const char *FLAGS[] = {
    "-t",
    "-s",
    "-d"};

typedef enum
{
    NONE,
    OBJ
} SourceType;

typedef struct
{
    void *ptr;
    size_t size_bytes;
} MappedFile;

bool 
map_file(MappedFile *file, char *path)
{
    int file_desc = open(path, O_RDONLY);
    if (file_desc < 0)
        return false;
    struct stat status;
    if (fstat(file_desc, &status) < 0)
    {
        close(file_desc);
        return false;
    }
    char *mapped_ptr = mmap(NULL, status.st_size, PROT_READ, MAP_PRIVATE, file_desc, 0);
    if (mapped_ptr == MAP_FAILED)
    {
        close(file_desc);
        return false;
    }
    file->size_bytes = status.st_size;
    file->ptr = mapped_ptr;
    return true;
}

typedef struct
{
    char padding[];
    
} VertexView;

bool
translate_to_hmodl(MappedFile file)
{
    size_t v, f, vn, vbo, fbo, vnbo = 0;
    for (uint32_t i = 0; i < file.size; i++)
    {
        switch (file->ptr[i])
        {
            case 'v':
                v += file_ptr->[i + 1] == 'n';
                vn += file_ptr->[i + 1] == 'n';
                break;
            case 'f':
                f++;
                break;
        }
    }
    char *hmodl = malloc(HMODL_HEADER_SIZE_BYTES + v + f + vn);
    
    





}

int 
main()
{
    char *sources[] = {
        #include "sources.txt"
    };
    const uint32_t num_sources = sizeof(sources) / sizeof(char *);

    MappedFile file;
    if (!map_file(&file, "source.txt"))
    {
        PRINT_ERROR("Cannot open file");
    }

    translate_to_hmodl(file);
    



    return 0;
}