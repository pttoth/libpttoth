template<typename T1, typename T2>
struct Tuple2{
	T1 _1;
	T2 _2;
	
	Tuple2(T1 p1, T2 p2):
			_1(p1), _2(p2){
	}
};


template<typename T1, typename T2, typename T3>
struct Tuple3{
	T1 _1;
	T2 _2;
	T3 _3;
	
	Tuple3(T1 p1, T2 p2, T3 p3):
			_1(p1), _2(p2), _3(p3){
	}
};


template<typename T1, typename T2, typename T3, typename T4>
struct Tuple4{
	T1 _1;
	T2 _2;
	T3 _3;
	T4 _4;
	
	Tuple4(T1 p1, T2 p2, T3 p3, T4 p4):
			_1(p1), _2(p2), _3(p3), _4(p4){
	}
};


template<typename T1, typename T2, typename T3, typename T4, typename T5>
struct Tuple5{
	T1 _1;
	T2 _2;
	T3 _3;
	T4 _4;
	T5 _5;
	
	Tuple5(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5):
			_1(p1), _2(p2), _3(p3), _4(p4), _5(p5){
	}
};
