# test loading module
import @PROJECT_NAME@

# test module functions
assert @PROJECT_NAME@.add(1, 2) == 3, 'Failed to add'
assert @PROJECT_NAME@.sub(3, 2) == 1, 'Failed to subtract'
