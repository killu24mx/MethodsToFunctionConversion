#include<iostream>


struct R{
    int a = 3;
    int b = 2;
    int sum(int c){return a + b + c;}
};

struct MethodPtr{
    void* func_ptr = nullptr;
    std::size_t offset = 0;
};

template<typename _ClassName,typename _Ret,typename... _Params>
decltype(auto) GetFuncPtr( _Ret(_ClassName::*ptr)(_Params...)){
     MethodPtr* m_ptr = reinterpret_cast<MethodPtr*>(&ptr); //преобразование адреса указателя на метод в указатель на структуру MethodPtr
     return reinterpret_cast<_Ret(*)(_ClassName*,_Params...)>(m_ptr->func_ptr); 
}


int main(int argc,char** argv)
{
    R r;

    auto func_ptr = GetFuncPtr(&R::sum);

    std::cout << func_ptr(&r,8) << "\n"; //out : 13
}
