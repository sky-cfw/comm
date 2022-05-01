/*
 * @Author: sky
 * @Date: 2022-05-01 16:12:13
 * @LastEditTime: 2022-05-01 18:32:42
 * @LastEditors: Please set LastEditors
 * @Description: 
 * 1）查看vector内存分配策略
 * 2）清空vector所占用的内存
 * @FilePath: /comm/language/cpp/stl/vector_clear_memory.cpp
 */

#include <iostream>
#include <vector>
using namespace std;

#define PRINT_VEC_SIZE(v) do {\
    cout << "size[" << v.size() << "] capacity[" << v.capacity() << "]" << endl;\
}while(0)

int insert_element( const int &element_num, std::vector<int> &vec_tmp ){
    //查看容量和大小
    cout << "------------------ 内存分配策略 -----------------" << endl;
    for(size_t i = 0; i < element_num; i++) {
        vec_tmp.push_back(i);
        PRINT_VEC_SIZE(vec_tmp);
    }

    return 0;
}

int clear_memory( const int &element_num ) {
    
    cout << endl << endl << "------------------ 清空vector占用内存 -----------------" << endl;
    
    //插入初始数据
    std::vector<int> vec_tmp;
    insert_element(element_num, vec_tmp);
    
    //清空vector所占用的内存
    // vec_tmp.resize(0);
    // cout << "------------------ resize to 0 -----------------" << endl;
    // PRINT_VEC_SIZE(vec_tmp);
    
    vec_tmp.clear();
    cout << "------------------ clear -----------------" << endl;
    PRINT_VEC_SIZE(vec_tmp);

    vec_tmp.shrink_to_fit();
    cout << "------------------ clear && shrink_to_fit -----------------" << endl;
    PRINT_VEC_SIZE(vec_tmp);

    return 0;
}

int shrink_to_fit_strategy( const int &element_num ){
    cout << endl << endl;
    cout << "------------------ shrink_to_fit函数根据size自适应调整capacity策略 -----------------" << endl;
    
    //插入初始数据
    std::vector<int> vec_tmp;
    insert_element(element_num, vec_tmp);

    //
    cout << "------------------ shrink_to_fit函数自适应调整capacity策略 -----------------" << endl;
    while( !vec_tmp.empty() ){
        vec_tmp.pop_back();
        vec_tmp.shrink_to_fit();
        PRINT_VEC_SIZE(vec_tmp);
    }

    return 0;
}

int main(int argc, char const *argv[]) {
    if ( argc < 3 ) {
        cout << "Usage: " << endl;
        cout << "1 清空vector占用内存: ./vector_clear_memory 2 <element_num>" << endl;
        cout << "2 shrink_to_fit函数根据size自适应调整capacity策略: ./vector_clear_memory 3 <element_num>" << endl;
        return 0;
    }
    int opt = atoi( argv[1] );
    size_t element_num = atoi( argv[2] );

    switch (opt) {
        case 1:{//清空vector占用内存
            clear_memory( element_num );
            break;
        }
        case 2:{//shrink_to_fit函数根据size自适应调整capacity策略
            shrink_to_fit_strategy( element_num );
            break;
        }
        default:{
            cout << "default break" << endl;
            break;
        }
            
    }

    return 0;
}
