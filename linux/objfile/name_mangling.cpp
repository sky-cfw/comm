/*name mangling*/

int func(int);
float func(float);

class C {
	int func(int);
	class C2 {
		float func(float);
	};
};

namespace N {
	int func(int );
	class C {
		int func(int);
	};
}
