#include <opencv2/opencv.hpp>
#include "res/Lab7/Code/panoramic_utils.cpp"

using namespace cv;
using namespace std;

/*
void projExample() {
	Mat img = imread("res/Lab7/Datasets/kitchen/i01.bmp");
	imshow("input", img);
	Mat out = cylindricalProj(img, 33);
	imshow("output", out);
	waitKey();
}//projExample
*/

/* loadImages() */
vector<Mat> loadImages(String path, const int IMAGE_NUM) {
	vector<Mat> images;

	for (int index = 0; index < IMAGE_NUM; index++) {
		
		path.append("" + to_string(index + 1) + ".png");
		images.push_back(imread(path));
		
		if (!images[index].data) {
			cout << "images datar not loaded properly" << endl;
			return vector<Mat>();
		}//if

		cout << path + "\n";
		path.pop_back();
		path.pop_back();
		path.pop_back();
		path.pop_back();

		path.pop_back();
		if (index+1 >= 10) {path.pop_back();}

	}//for
	return images;
}//loadImages

/* visualizeImages() */
void visualizeImages(vector<Mat> &images) {
	vector<Mat>::iterator iter;
	for (iter = images.begin(); iter != images.end(); iter++) {
		imshow("dolomites", *iter);
		waitKey();
	}//for
}//visualizeImages

/* projectImages */
vector<Mat> projectImages(vector<Mat> &images, double angle) {
	vector<Mat> projImages;
	for (int index = 0; index < images.size(); index++) {
		projImages.push_back(cylindricalProj(images[index], angle));
	}//for
	return projImages;
}//projects

/* extractFeatures() */
void extractFeatures(vector<Mat> &images) {

	//Feature detector
	Ptr<FeatureDetector> sift_detector = SIFT::create();
	vector<vector<KeyPoint>> keypoints_images = vector<vector<KeyPoint>>();
	
	//Descriptor extractor
	Ptr<DescriptorExtractor> sift_extractor = SIFT::create();
	Mat descriptors_images;

	for (int index = 0; index < images.size(); index++) {
		sift_detector->detect(images[index], keypoints_images[index]);
		//sift_extractor->compute(images[index], keypoints_images, descriptors_images);
	}//for
	sift_detector.release();
	sift_extractor.release();

	/*// Create Brute-Froce Matcher
	BFMatcher bfm = BFMatcher(NORM_L2, true);

	// Vector where matches will be stored
	vector<DMatch> matches;
	Mat output_image;
	for (int index = 0; index < images.size() - 1; index++) {
		bfm.match(descriptors_images, descriptors_images, matches);
		drawMatches(images[index], keypoints_images[index], images[index + 1], keypoints_images[index + 1], matches, output_image);
	}//for*/
	
}//extractFeatures

void PanoramicImage(vector<Mat> &imgs) {

	Mat pano;

	Ptr<Stitcher> stitcher = Stitcher::create(Stitcher::PANORAMA);

	Stitcher::Status status = stitcher->stitch(imgs, pano);
	
	imshow("Result", pano);
	waitKey();
	
}//computeMatching

int main() {
	vector<Mat> images = loadImages("res/Lab7/Datasets/dolomites/", 23);
	//projectImages(images, 27);
	//extractFeatures(images);
	PanoramicImage(images);
	//visualizeImages(images);
	//projExample();
	//prova();
	return 0;
}//main

