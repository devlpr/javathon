class Javathon
{
  public native int startPython();
  public native int handleEvent(String json);
  public native int stopPython();

  static
  {
    System.loadLibrary("JavathonImp"); 
  }
}

