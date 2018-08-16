#! /bin/bash

# Simple test for the 2048 program.

run () {
  echo "$*"
  if $*
  then echo 'success'
  else echo 'error'
  fi
}

run ./2048 <<EOF
-3 15 -8 29 17
EOF

run ./2048 <<EOF
l i j k
EOF

run ./2048 <<EOF
EOF

run ./2048 <<EOF
llll
EOF

exit 0
