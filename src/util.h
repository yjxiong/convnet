#ifndef UTIL_H_
#define UTIL_H_

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef __USE_GNU
#define __USE_GNU
#endif

#include <string>
#define cimg_use_jpeg
#define cimg_use_lapack
#include "CImg.h"
#include "cudamat.cuh"
#include <stdio.h>
#include <google/protobuf/text_format.h>
#include "convnet_config.pb.h"
#include "hdf5.h"
#include <signal.h>
#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ucontext.h>
#include <unistd.h>

using namespace cimg_library;
using namespace std;

// Outputs a string that describes the err_code.
string GetStringError(int err_code);
// Reads model_file from the disk and instantiates a Model.
void ReadModel(const string& model_file, config::Model& model);
void ReadModelText(const string& model_file, config::Model& model);
void ReadDataConfig(const string& data_config_file, config::DatasetConfig& data_config);
void ReadLayerConfig(const string& layer_config_file, config::Layer& layer_config);
void WriteModelBinary(const string& output_file, const config::Model& model);
void ReadModelBinary(const string& input_file, config::Model& model);
void WriteHDF5CPU(hid_t file, float* mat, int rows, int cols, const string& name);
void ReadHDF5IntAttr(hid_t file, const string& name, int* val);
void WriteHDF5IntAttr(hid_t file, const string& name, const int* val);

// mat must already be allocated. Use ReadHDF5Shape to figure out the shape, if needed.
void ReadHDF5CPU(hid_t file, float* mat, int size, const string& name);
void ReadHDF5Shape(hid_t file, const string& name, int* rows, int* cols);
void ReadHDF5ShapeFromFile(const string& file_name, const string& dataset_name, int* rows, int* cols);

void SetupBackTraceHandler();
void WaitForEnter();
int Bound(int val, int lb, int ub);
string GetTimeStamp();
void TimestampModelFile(const string& src_file, const string& dest_file, const string& timestamp);

bool ReadLines(const string& filename, vector<string>& lines);


class ImageDisplayer {
 public:
  ImageDisplayer();
  ImageDisplayer(int width, int height, int num_colors, bool show_separate, const string& name);
  ~ImageDisplayer() { delete main_disp; delete disp; }
  void SetTitle(const string& title) {title_ = title;}
  void DisplayImage(float* data, int spacing, int image_id);
  void DisplayWeights(float* data, int size, int num_filters, int display_size, bool yuv = false);
  //void DisplayWeightStats(float* data, int size);
  //void DisplayMathGL(mglGraph& gr);
  CImgDisplay* main_disp, *disp;

  static void YUVToRGB(const float* yuv, float* rgb, int spacing);
  static void RGBToYUV(const float* rgb, float* yuv, int spacing);

 private:
  int width, height, num_colors;
  bool show_separate;
  string title_;
};


#endif
