class Main 
{
  public static void main(String[] args) 
  {
    Javathon python = new Javathon();

    // Required to get the interpreter running
    python.startPython();

    System.out.format("RETURN VALUE IN JVM: %s\n",
                      python.handleEvent("{JSON: Fools}"));

    // Required to shut it down
    python.stopPython();
  }
}

