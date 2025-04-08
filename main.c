#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG 1

double findMedianSortedArrays(int nums1[], int size, int nums2[], int size2);

#define TEST_DATA_SIZE 2
int** test_data();
int*  test_results();

struct RESULT {
    bool   success;
    double result;
};

int main() {

#ifdef RUN_TESTS
#else

    int    nums[  2 ] = { 1, 2 };
    int    nums2[ 2 ] = { 3, 4 };
    double shldb      =   2.5;

    double result = findMedianSortedArrays(nums, 2, nums2, 2);

    printf("result: %f  should be: %f\n", result,shldb);

    return 0;
#endif
}



int*** test_data() {
    static int tdata[TEST_DATA_SIZE][2][30] = {
                        {{1,2,7,12,35,66,69,75,77,88,93,95,97},{3,4,5,15,20,45,88}},
                        {{1,2,7,12,35,66,69,75,77,88,93,95},   {3,4,5,15,20,45,88}}
    }
}

int** test_data_size() {
    static int tdatasz[TEST_DATA_SIZE][2] = {
        {13,7},
        {12,7}
    }
}


int limit(int pos, int size) {
    if (pos < 0)     return 0;
    if (pos >= size) return size - 1;
}


#include <stdio.h>
#include <math.h>

void equalize(int *pos, int *pos2, int nums[], int size, int nums2[], int size2, int odd) {
    int tot   = size + size2;

    int left  = *pos + *pos2 + 2;

    #ifdef DEBUG
    int right = tot - left;
    printf("total length:%d   left:%d   right:%d\n", tot, left, right);
    #endif

    int middle = (int)(tot / 2.0 + 0.5);
    int move   = middle - left;

    #ifdef DEBUG
    if (move > 0) {
        printf("---->   %d\n", move);
    } else if (move < 0) {
        printf("<----   %d\n", move);
    } else {
        printf(">-*-<   %d\n", move);
    }
    #endif

    if (odd) {
        *pos  += (int)((double)size  * (double)move / (double)tot);
        *pos2 += (int)((double)size2 * (double)move / (double)tot);
    } else {
        double move0 = (double)size  * (double)move / (double)tot;
        double move1 = (double)size2 * (double)move / (double)tot;
        if ((double)move0 - (double)((int)move0) == 0.5) {
            *pos  += (int)(move0 + 0.5);
            *pos2 += (int)move1;
        } else {
            *pos  += (int)(move0 + 0.5);
            *pos2 += (int)(move1 + 0.5);
        }
    }

    if (*pos  > size ) *pos  = size;
    if (*pos2 > size2) *pos2 = size2;

    if (*pos  < -1) *pos  = -1;
    if (*pos2 < -1) *pos2 = -1;

    #ifdef DEBUG
    left  = *pos + *pos2 + 2;
    right = tot - left;
    printf("                      left:%d   right:%d\n", left, right);
    #endif
}


void get_closer(int *pos, int nums[], int pos2, int nums2[], int *inc, int size, int size2) {
    int movement = 0;

    *pos  = limit( *pos,  size  );
     pos2 = limit(  pos2, size2 );

    if (nums[*pos] < nums2[pos2]) {

        #ifdef DEBUG
        printf("%d < %d\n", nums[*pos], nums2[pos2]);
        #endif

        movement = *inc;
        *pos    += movement;

        #ifdef DEBUG
        printf("->\n");
        #endif

    } else if (nums[*pos] > nums2[pos2]) {

        #ifdef DEBUG
        printf("%d > %d\n", nums[*pos], nums2[pos2]);
        #endif

        movement = *inc;
        *pos -= movement;

        #ifdef DEBUG
        printf("<-\n");
        #endif

    }

    if (*inc > 1) {
        *inc = (int)(*inc / 2.0 + 0.5);
    }

    #ifdef DEBUG
    printf("%d %d %d\n", *pos, movement, *inc);
    #endif

}



double median(int* nums, int size) {
    if (size % 2 == 0) {
        return (nums[size / 2 - 1] + nums[size / 2]) / 2.0;
    } else {
        return nums[size / 2];
    }
}




struct RESULT check_end(int pos, int nums[], int pos2, int nums2[], int odd, int size, int size2) {
    struct RESULT result;
    result.success = false;

    int last = size - 1;

    if (odd) {
        if (pos > last) {
            fprintf(stderr, "could be here\n");
            exit(EXIT_FAILURE);
        } else if (pos == last) {
            if (pos2 < size2 - 1) {
                printf("Achk: %d <= %d <= %d\n", nums2[pos2], nums[pos], nums2[pos2 + 1]);
            }

            if (nums2[pos2] <= nums[pos] && nums[pos] <= nums2[pos2 + 1]) {
                result.success = true;
                result.result  = nums[pos];
                return result;

            } else if (nums[pos] <= nums2[pos2]) {
                result.success = true;
                result.result  = nums2[pos2];
                return result;
            }

        } else {
            if (pos < 0) {
                result.success = true;
                result.result = nums2[pos2];
                return result;

            } else {
                printf("Bchk: %d <= %d <= %d\n", nums[pos], nums2[pos2], nums[pos + 1]);

                if (nums[pos] <= nums2[pos2] && nums[pos + 1] >= nums2[pos2]) {
                    result.success = true;
                    result.result = nums2[pos2];
                    return result;
                }
            }
        }


    } else { // even
        if (pos > last) {
            if (pos2 < size2 - 2) {
                result.success = true;
                result.result  = (nums2[pos2] + nums2[pos2 + 1]) / 2.0;
                return result;

            } else {
                result.success = true;
                result.result  = (nums2[pos2] + nums[pos - 1]) / 2.0;
            }

        } else if (pos == last) {
            if (pos2 >= size2) {
                fprintf(stderr, "needs code 1\n");
                exit(EXIT_FAILURE);

            } else if (pos2 == size2 - 1) {
                fprintf(stderr, "needs code 2\n");
                exit(EXIT_FAILURE);

            } else if (pos2 < 0) {
                result.success = true;
                result.result  = (nums[pos] + nums2[0]) / 2.0;
                return result;

            }

            if (nums[pos] >= nums2[pos2]) {
                if (nums2[pos2] == nums[pos]) {
                    result.success = true;
                    result.result  = (double)nums[pos];

                } else if (nums2[pos2 + 1] > nums[pos]) {
                    result.success = true;
                    result.result  = (nums[pos] + nums2[pos2 + 1]) / 2.0;
                }

            } else {
                result.success = true;
                result.result  = (nums2[pos2] + nums2[pos2 + 1]) / 2.0;
                return result;
            }

        } else if (pos < 0) {
            if (pos2 + 1 < size2) {
                if (nums[0] < nums2[pos2 + 1]) {
                    result.success = true;
                    result.result  = (nums[0] + nums2[pos2]) / 2.0;
                    return result;

                } else {
                    result.success = true;
                    result.result  = (nums2[pos2] + nums2[pos2 + 1]) / 2.0;
                }

            } else {
                if (pos2 > size2 - 1) {
                    result.success = true;
                    result.result  = (nums[0] + nums2[pos2 - 1]) / 2.0;
                    return result;

                } else {
                    result.success = true;
                    result.result  = (nums[0] + nums2[pos2]) / 2.0;
                    return result;
                }
            }

        } else if (nums[pos] <= nums2[pos2] && nums2[pos2] <= nums[pos + 1]) {
            if (pos2 <= size2 - 2) {
                if (nums[pos + 1] <= nums2[pos2 + 1]) {
                    result.success = true;
                    result.result  = (nums2[pos2] + nums[pos + 1]) / 2.0;
                    return result;
                } else {
                    result.success = true;
                    result.result  = (nums2[pos2] + nums2[pos2 + 1]) / 2.0;
                    return result;
                }
            } else if (nums[pos + 1] >= nums2[pos2]) {
                result.success = true;
                result.result  = (nums2[pos2] + nums[pos + 1]) / 2.0;
                return result;
            }
        } else if (pos2 <= size2 - 2) {
            if (nums[pos] > nums2[pos2] && nums2[pos2 + 1] >= nums[pos]) {
                if (nums[pos + 1] >= nums2[pos2 + 1]) {
                    result.success = true;
                    result.result  = (nums[pos] + nums2[pos2 + 1]) / 2.0;
                    return result;
                } else {
                    result.success = true;
                    result.result  = (nums[pos] + nums[pos + 1]) / 2.0;
                    return result;
                }
            }
        } else if (nums[pos] > nums2[pos2]) {
            result.success = true;
            result.result  = (nums[pos] + nums[pos + 1]) / 2.0;
            return result;
        } else if (nums[pos + 1] >= nums2[pos2]) {
            result.success = true;
            result.result  = (nums2[pos2] + nums[pos + 1]) / 2.0;
            return result;
        }
    }
    return result; // Return 0 if no condition is met
}

double findMedianSortedArrays(int nums[], int size, int nums2[], int size2) {
    int total_size = size + size2;
    int odd = total_size % 2 > 0;

    struct RESULT result;

    //int* arynums[2] = {nums1, nums2};
    //int arypos[2] = {0, 0};
    int pos, pos2, inc, inc2;

    if (size % 2 == 0 && size2 % 2 == 0) {
        pos  = size  / 2 - 1;
        pos2 = size2 / 2 - 1;
    } else {
        if (size  > size2) {
            pos  = size  / 2 - 1;
            pos2 = size2 / 2;
        } else {
            pos  = size  / 2;
            pos2 = size2 / 2 - 1;
        }
    }

    inc  = size  / 4;
    inc2 = size2 / 4;
    if (inc  == 0) inc  = 1;
    if (inc2 == 0) inc2 = 1;

    // Some edge cases
    if (size  == 0) return median( nums2, size2 );
    if (size2 == 0) return median( nums,  size  );

    bool reverse = false;

    int max_iterations = 1000;
    while (max_iterations-- > 0) {

        if (reverse) {
            result = check_end(pos2, nums2, pos, nums, odd, size2, size);
        } else {
            result = check_end(pos, nums, pos2, nums2, odd, size, size2);
        }

        if (result.success) return result.result;

        if (reverse) {
            reverse = false;
        } else {
            reverse = true;
        }

        if (reverse) {
            result = check_end(pos2, nums2, pos, nums, odd, size2, size);
        } else {
            result = check_end(pos, nums, pos2, nums2, odd, size, size2);
        }

        if (result.success) return result.result;

        if (reverse) {
            get_closer(&pos2, nums2, pos,  nums,  &inc2, size2, size);
        } else {
            get_closer(&pos,  nums,  pos2, nums2, &inc,  size,  size2);
        }

        equalize(&pos, &pos2, nums, size, nums2, size2, odd);
    }

    return 0.0; // Placeholder return
}