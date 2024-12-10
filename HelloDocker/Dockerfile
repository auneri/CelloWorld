FROM ubuntu:20.04
RUN apt-get update --yes
RUN apt-get install --yes clang cmake
ENV ISDOCKER=1
COPY . ./src
RUN cmake -S ./src -B ./bin
RUN cmake --build ./bin
CMD ["cmake", "--build", "./bin", "--target", "test"]
