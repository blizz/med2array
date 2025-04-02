#include <stdio.h>

double findMedianSortedArrays(int* nums1, int size1, int* nums2, int size2);

struct RESULT {
    bool   success;
    double result;
};

int main() {
    // printf() displays the string inside quotation
    printf("Hello, World!");


    int    nums[  2 ] = { 1, 2 };
    int    nums2[ 2 ] = { 3, 4 };
    double shldb      =   2.5;

    double result = findMedianSortedArrays(nums, 2, nums2, 2);

    printf("result: %f\n", result);

    return 0;
}



double median(int* nums, int size) {
    if (size % 2 == 0) {
        return (nums[size / 2 - 1] + nums[size / 2]) / 2.0;
    } else {
        return nums[size / 2];
    }
}




struct RESULT check_end(int pos, int nums[], int pos2, int nums2[], int odd, int nums_size, int nums2_size) {
    STRUCT RESULT result;
    result.success = false;

    int last = nums_size - 1;

    if (odd) {
        if (pos > last) {
            fprintf(stderr, "could be here\n");
            exit(EXIT_FAILURE);
        } else if (pos == last) {
            if (pos2 < nums2_size - 1) {
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
                return nums2[pos2];

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
                if (pos2 > nums2_size - 1) {
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
            if (pos2 <= nums2_size - 2) {
                if (nums[pos + 1] <= nums2[pos2 + 1]) {
                    return (nums2[pos2] + nums[pos + 1]) / 2.0;
                } else {
                    return (nums2[pos2] + nums2[pos2 + 1]) / 2.0;
                }
            } else if (nums[pos + 1] >= nums2[pos2]) {
                return (nums2[pos2] + nums[pos + 1]) / 2.0;
            }
        } else if (pos2 <= nums2_size - 2) {
            if (nums[pos] > nums2[pos2] && nums2[pos2 + 1] >= nums[pos]) {
                if (nums[pos + 1] >= nums2[pos2 + 1]) {
                    return (nums[pos] + nums2[pos2 + 1]) / 2.0;
                } else {
                    return (nums[pos] + nums[pos + 1]) / 2.0;
                }
            }
        } else if (nums[pos] > nums2[pos2]) {
            return (nums[pos] + nums[pos + 1]) / 2.0;
        } else if (nums[pos + 1] >= nums2[pos2]) {
            return (nums2[pos2] + nums[pos + 1]) / 2.0;
        }
    }
    return 0; // Return 0 if no condition is met
}

double findMedianSortedArrays(int nums1[], int size1, int nums2[], int size2) {
    int total_size = size1 + size2;
    int odd = total_size % 2 > 0;

    //int* arynums[2] = {nums1, nums2};
    //int arypos[2] = {0, 0};
    int pos, pos2, inc, inc2;

    if (size1 % 2 == 0 && size2 % 2 == 0) {
        pos  = size1 / 2 - 1;
        pos2 = size2 / 2 - 1;
    } else {
        if (size1 > size2) {
            pos  = size1 / 2 - 1;
            pos2 = size2 / 2;
        } else {
            pos  = size1 / 2;
            pos2 = size2 / 2 - 1;
        }
    }

    inc  = size1 / 4;
    inc2 = size2 / 4;
    if (inc  == 0) inc  = 1;
    if (inc2 == 0) inc2 = 1;

    // Some edge cases
    if size  == 0 return median( nums2, size2 );
    if size2 == 0 return median( nums,  size  );

    bool reverse = false;

    int movement  = 1;
    int movement2 = 1;

    while (movement != 0 || movement2 != 0) {
        double res = check_end( pos, nums, pos2, nums2, odd, size, size2 );
        if (res != 0) return res;

        if (working_on[0] == 0) {
            working_on[0] = 1;
            working_on[1] = 0;
        } else {
            working_on[0] = 0;
            working_on[1] = 1;
        }

        res = check_end(arypos[working_on[0]], arynums[working_on[0]], arypos[working_on[1]], arynums[working_on[1]], odd);
        if (res != 0) return res;

        int* closer = get_closer(arypos[working_on[0]], arynums[working_on[0]], arypos[working_on[1]], arynums[working_on[1]], aryinc[working_on[0]]);
        arypos[working_on[0]] = closer[0]; // Assuming get_closer returns an array with the new position
        movement[working_on[0]] = equalize(arypos, arynums, odd);
    }

    return 0.0; // Placeholder return
}