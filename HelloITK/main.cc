#include <iostream>

#include <itkImage.h>


int main(int, char *[]) {

  typedef itk::Image<unsigned short, 3> ImageType;
  ImageType::Pointer image = ImageType::New();

  std::cout << image << std::endl;

  return 0;
}
