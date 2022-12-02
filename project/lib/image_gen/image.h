#ifndef LIB_IMG
#define LIB_IMG

class image {
	public:
	image(int width, int height);
	~image(void);
	void set_point (int x, int y, char colour);
	void save (std::string filename);
	void circle (int origin_x, int origin_y, int r);
	void circle (int origin_x, int origin_y, int r, char val);

	private:
	char *pixels;
	int width;
	int height;
};

#endif
