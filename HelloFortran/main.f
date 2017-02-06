!usr/bin/make -s "${0%.*}" && ./"${0%.*}" "$@"; s=$?; rm ./"${0%.*}"; exit $s

! use "bash ./main.f" to build and run the executable

      program main
          real(kind=16) :: x
          x=314159.d-5
          print *, 'hello, world', x
      end program main
