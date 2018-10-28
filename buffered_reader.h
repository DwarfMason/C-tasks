class BufferedReader {
 private:
  PackageStream *stream_;
  char *Buffer;
  int index = 0;
  int rem = 0;

 public:
  explicit BufferedReader(PackageStream *stream) :
      stream_(stream), Buffer(new char[stream_->PackageLen()]) {}

  int32_t Read(char *buf, int32_t bytes) {
    int i = 0;
    int len = 0;
    while (bytes != 0 && index != rem) {
      buf[i] = Buffer[index];
      i++;
      index++;
      len++;
      bytes--;
    }
    if (bytes > 0) {
      index = 0;
      rem = stream_->ReadPackage(Buffer);
      while (bytes != 0 && index != rem) {
        buf[i] = Buffer[index];
        i++;
        index++;
        len++;
        bytes--;
        if (index == stream_->PackageLen()) {
          rem = stream_->ReadPackage(Buffer);
          index = 0;
        }
      }
    }
    return len;
  }
};
