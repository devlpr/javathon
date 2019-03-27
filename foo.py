

def foo(json):
    try:
        print "\n\nIn Python: ", json
        return True
    except Exception, e:
        return False
