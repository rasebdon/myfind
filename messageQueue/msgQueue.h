#define KEY 13377331
#define PERM 0660

#define MAX_DATA 512

typedef struct
{
	long mType;
	char relativePath[MAX_DATA];
    int childPId;
} message_t;