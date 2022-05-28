/*
 * @Author: sky wcf0118@gmail.com
 * @Date: 2022-05-18 23:27:29
 * @LastEditors: sky wcf0118@gmail.com
 * @LastEditTime: 2022-05-18 23:39:55
 * @FilePath: /comm/leetcode/02_array/left_right_border.cpp
 * @Description: 排序数组查找元素的第一个和最后一个位置 https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/
 */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        
        // 3种情况
        // 1.target在nums范围的左边或右边
        // 2.target在nums范围中，但nums中不存在target 表现为
        // 3.target在nums范围中，但nums中存在target
        int leftBorder = getLeftBorder(nums, target);
        int rightBorder = getRightBorder(nums, target);

        if ( -2 == leftBorder || -2 == rightBorder ) {
            return {-1, -1};
        } else if ( rightBorder - leftBorder > 1 ) {
            return {leftBorder+1, rightBorder-1};
        } else {
            cout << "left:" << leftBorder << endl << "right:" << rightBorder << endl;
            return {-1, -1};
        }
    }

private:
    int getLeftBorder(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int leftBorder = -2;//为什么设置初始值-2？识别 target在nums范围的右侧
        while( left <= right ) {
            int mid = left + (right-left)/2;
            if ( nums[mid] < target ) {
                left = mid + 1;
            } else {
                right = mid -1;
                leftBorder = right;
            }
        }

        return leftBorder;
    }

    int getRightBorder(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int rightBorder = -2;//为什么设置初始值-2？识别target在nums范围的左侧
        while( left <= right ) {
            int mid = left + (right-left)/2;
            if ( nums[mid] <= target ) {
                left = mid + 1;
                rightBorder = left;
            } else {
                right = mid -1;
            }
        }

        return rightBorder;
    }
};

int main(int argc, char const *argv[]) {
    
    int target = 7;
    vector<int> nums = {5, 7, 7, 8, 8, 10};
    
    Solution solution;
    vector<int> index = solution.searchRange( nums, target );
    
    // 打印左右边界的索引
    for ( const auto &i : index ) {
        cout << i << endl;
    }

    return 0;
}
