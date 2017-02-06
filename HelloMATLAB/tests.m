% test loading library
if isunix
    library = 'lib@PROJECT_NAME@Library';
elseif ispc
    library = '@PROJECT_NAME@Library';
else
    error('Platform is not supported');
end
loadlibrary(library, '@PROJECT_NAME@Library.h');
assert(libisloaded(library), 'Failed to load library');

% test library functions
assert(calllib(library, 'add', 1, 2) == 3, 'Failed to add');
assert(calllib(library, 'sub', 3, 2) == 1, 'Failed to subtract');
