class HelloWorld 
{
  public native void displayMessage();
  static 
  {
    System.loadLibrary("HelloWorldImp"); 
  }
}

