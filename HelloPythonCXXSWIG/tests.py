import HelloPythonCXXSWIG

library = HelloPythonCXXSWIG.Library(1)
assert library.add(2) == 3, 'Failed to add'
assert library.sub(2) == 1, 'Failed to subtract'
del library
