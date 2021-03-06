#include <cstdio>
#include <cmath>
#include <algorithm>

double Render_Main(double x, double y) {
	double m = x * x + y * y, t = 5 * atan2(x, y);
	double r = .5221-.2944*cos(t)-.02483*cos(2*t)+.05337*cos(3*t)-.01529*cos(4*t)-.0195*cos(5*t)+.01284*cos(6*t)+.003285*cos(7*t)-.009388*cos(8*t)+.001775*cos(9*t)+.004718*cos(10*t);
	return 60 * std::min(std::max(m-1.7,1.45-m), sqrt(m)-r);
}

int main(int argc, char *argv[]) {
	FILE* fp = fopen(argv[1], "wb");
	fwrite("\x89PNG\r\n\x1A\n\0\0\0\rIHDR\0\0\2X\0\0\x1\x90\x8\2\0\0\0\xFDW\x89\xCF\0\xB\5\xE6IDATx\x1", 1, 43, fp);
	for (int j = 0; j < 400; j++) {
		fwrite("\0\x9\7\xF6\xF8\0", 1, 6, fp);
		for (int i = 0; i < 600; i++) {
			double t = Render_Main(.01*(i-300), .01*(j-200));
			t = (t > 1 ? 0 : t < 0 ? 1 : 1 - t);
			fputc(250*t,fp); fputc(220*t,fp); fputc(5*t,fp);
		}
	}
	fwrite("V2'\xAF\x65\xCE\x18\r\0\0\0\0IEND\xAE\x42`\x82", 1, 20, fp);
	fclose(fp); return 0;
}
