#include <limits.h>
#include <string.h>

/* determine if all 'a' chars are before 'b' chars */
bool isabord(char *s)
{
	char *a_ptr = strrchr(s, 'a');
	char *b_ptr = strchr(s, 'b');
	if (a_ptr == NULL || b_ptr == NULL) {
		return 1;
	}
	return a_ptr < b_ptr;
}

/* return the biggest number in an array divisable by `divisior` */
int maxdvby(int nums[], int divisor)
{
	int max = INT_MIN;
	unsigned long arrsize = sizeof(nums) / sizeof(int);
	for (int i = 0; i < arrsize; i++) {
		if (nums[i] > max && nums[i] % divisor == 0)
			max = nums[i];
	}
	return max;
}