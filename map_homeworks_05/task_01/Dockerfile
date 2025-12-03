FROM ubuntu:16.04
RUN apt-get update && \
    apt-get install -y g++ nano
WORKDIR /app
COPY main.cpp .
RUN g++ -o hello main.cpp
CMD ["./hello"]
