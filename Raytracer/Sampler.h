#ifndef H_Sampler
#define H_Sampler

class Sampler
{
private:
	int x, y;

public:
	Sampler();
	Sampler(int x, int y);
	int getX();
	int getY();
};

#endif // !H_Sampler