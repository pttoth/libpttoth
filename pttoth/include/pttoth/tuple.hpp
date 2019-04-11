#pragma once

namespace pttoth{

template<typename T1, typename T2>
struct Tuple2{
    T1 _1; T2 _2;

    Tuple2(T1 p1, T2 p2):
            _1(p1), _2(p2){
    }
};


template<typename T1, typename T2, typename T3>
struct Tuple3{
    T1 _1; T2 _2; T3 _3;

    Tuple3(T1 p1, T2 p2, T3 p3):
            _1(p1), _2(p2), _3(p3){
    }
};


template<typename T1, typename T2, typename T3, typename T4>
struct Tuple4{
    T1 _1; T2 _2; T3 _3; T4 _4;

    Tuple4(T1 p1, T2 p2, T3 p3, T4 p4):
            _1(p1), _2(p2), _3(p3), _4(p4){
    }
};


template<typename T1, typename T2, typename T3, typename T4, typename T5>
struct Tuple5{
    T1 _1; T2 _2; T3 _3; T4 _4; T5 _5;

    Tuple5(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5):
            _1(p1), _2(p2), _3(p3), _4(p4), _5(p5){
    }
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct Tuple6{
    T1 _1; T2 _2; T3 _3; T4 _4; T5 _5; T6 _6;

    Tuple6(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6):
            _1(p1), _2(p2), _3(p3), _4(p4), _5(p5), _6(p6){
    }
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct Tuple7{
    T1 _1; T2 _2; T3 _3; T4 _4; T5 _5; T6 _6; T7 _7;

    Tuple7(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7):
            _1(p1), _2(p2), _3(p3), _4(p4), _5(p5), _6(p6), _7(p7){
    }
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct Tuple8{
    T1 _1; T2 _2; T3 _3; T4 _4; T5 _5; T6 _6; T7 _7; T8 _8;

    Tuple8(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8):
            _1(p1), _2(p2), _3(p3), _4(p4), _5(p5), _6(p6), _7(p7), _8(p8){
    }
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct Tuple9{
    T1 _1; T2 _2; T3 _3; T4 _4; T5 _5; T6 _6; T7 _7; T8 _8; T9 _9;

    Tuple9(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9):
            _1(p1), _2(p2), _3(p3), _4(p4), _5(p5), _6(p6), _7(p7), _8(p8), _9(p9){
    }
};

} //namespace pttoth
