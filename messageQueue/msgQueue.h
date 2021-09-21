#define KEY 420257999		/* eindeutiger Key z.B. Matrikelnummer */
#define PERM 0660

#define MAX_DATA 255

typedef struct
{
	long mType;
	char mText[MAX_DATA];
} message_t;