
class fuck
{
public:
	fuck() :name("jianghanxia"), times(10), pdouble(0),f(){}
	const std::string name;
	int times;
	double * pdouble;
	std::ifstream &  f;
};



int main(int argc, char* argv[])
{
	fuck fc;
	std::cout << fc.name << "\t" << fc.times <<std::endl;
	return 0;
}