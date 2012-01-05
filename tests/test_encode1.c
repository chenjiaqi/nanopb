/* A very simple encoding test case using person.proto.
 * Just puts constant data in the fields and encodes into
 * buffer, which is then written to stdout.
 */

#include <stdio.h>
#include <pb_encode.h>
#include "person.pb.h"

int main()
{
    /* Initialize the structure with constants */
    Person person = {{1 << Person_email_index},
        "Test Person 99", 99, "test@person.com",
        3, {{{1 << Person_PhoneNumber_type_index},
             "555-12345678", Person_PhoneType_MOBILE},
            {{1 << Person_PhoneNumber_type_index},
             "99-2342", 0},
            {{1 << Person_PhoneNumber_type_index},
             "1234-5678", Person_PhoneType_WORK},
        }};

    uint8_t buffer[512];
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    
    /* Now encode it and check if we succeeded. */
    if (pb_encode(&stream, Person_msg, &person))
    {
        fwrite(buffer, 1, stream.bytes_written, stdout);
        return 0; /* Success */
    }
    else
    {
        return 1; /* Failure */
    }
}
