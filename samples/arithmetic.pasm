set     I1, 10
set     N1, 42.0
inc     I1
inc     I1
inc     N1
inc     N1
print   I1
print   ", "
print   N1
print   "\n"
dec     I1
dec     I1
dec     I1
dec     N1
dec     N1
dec     N1
print   I1
print   ", "
print   N1
print   "\n"
set     I1, 2
set     I2, 4
add     I3, I1, I2  # I3 is now 6 (2+4)
print   I3
print   ", "
sub     I3, I1, I2  # I3 is now -2 (2-4)
print   I3
print   ", "
mul     I3, I1, I2  # I3 is now 8 (2*4)
print   I3
print   ", "
div     I3, I2, I1  # I3 is now 2 (4/2)
print   I3
print   ", "
add     I1, 5   # I1 is now 7
print   I1
print   ", "
set     N1, 1
set     N2, 3
div     N3, N1, N2  # N3 is now 0.333333
print   N3
print   "\n"
end