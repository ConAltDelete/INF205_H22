#ifndef LIB_IMG
#define LIB_IMG

class image {
	public:
	image(int width, int height);
	~image(void);
	int set_point (int x, int y, char colour);
	int save (std::string filename);
	int circle (int origin_x, int origin_y, int r);

	private:
	char *pixels;
	int width;
	int height;
};

#endif
