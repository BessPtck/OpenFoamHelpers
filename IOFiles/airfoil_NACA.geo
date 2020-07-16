boxdim = 4;
Point(1) = {1,-0, 0,0.01};
Point(2) = {0.998474,0.00032, 0,0.01};
Point(3) = {0.993903,0.00129, 0,0.01};
Point(4) = {0.986314,0.00289, 0,0.01};
Point(5) = {0.975752,0.00509, 0,0.01};
Point(6) = {0.962276,0.00784, 0,0.01};
Point(7) = {0.945966,0.0111, 0,0.01};
Point(8) = {0.926917,0.01481, 0,0.01};
Point(9) = {0.90524,0.01891, 0,0.01};
Point(10) = {0.881064,0.02332, 0,0.01};
Point(11) = {0.854532,0.02798, 0,0.01};
Point(12) = {0.825802,0.03282, 0,0.01};
Point(13) = {0.795047,0.03776, 0,0.01};
Point(14) = {0.762452,0.04272, 0,0.01};
Point(15) = {0.728216,0.04764, 0,0.01};
Point(16) = {0.692545,0.05245, 0,0.01};
Point(17) = {0.655659,0.05707, 0,0.01};
Point(18) = {0.617783,0.06143, 0,0.01};
Point(19) = {0.579153,0.06546, 0,0.01};
Point(20) = {0.540006,0.06911, 0,0.01};
Point(21) = {0.500587,0.0723, 0,0.01};
Point(22) = {0.461143,0.07497, 0,0.01};
Point(23) = {0.421921,0.07708, 0,0.01};
Point(24) = {0.383032,0.07854, 0,0.01};
Point(25) = {0.34468,0.07918, 0,0.01};
Point(26) = {0.307289,0.07893, 0,0.01};
Point(27) = {0.271106,0.07779, 0,0.01};
Point(28) = {0.236371,0.07579, 0,0.01};
Point(29) = {0.203313,0.07294, 0,0.01};
Point(30) = {0.172151,0.0693, 0,0.01};
Point(31) = {0.143089,0.06494, 0,0.01};
Point(32) = {0.116313,0.05991, 0,0.01};
Point(33) = {0.091996,0.05432, 0,0.01};
Point(34) = {0.070289,0.04825, 0,0.01};
Point(35) = {0.051324,0.0418, 0,0.01};
Point(36) = {0.035214,0.03507, 0,0.01};
Point(37) = {0.022051,0.02815, 0,0.01};
Point(38) = {0.011907,0.02112, 0,0.01};
Point(39) = {0.004833,0.01404, 0,0.01};
Point(40) = {0.00086,0.00699, 0,0.01};
Point(41) = {0,0, 0,0.01};
Point(42) = {0.002223,-0.00668, 0,0.01};
Point(43) = {0.007479,-0.01282, 0,0.01};
Point(44) = {0.015723,-0.0184, 0,0.01};
Point(45) = {0.026892,-0.0234, 0,0.01};
Point(46) = {0.040906,-0.02782, 0,0.01};
Point(47) = {0.057669,-0.03165, 0,0.01};
Point(48) = {0.077071,-0.03487, 0,0.01};
Point(49) = {0.098987,-0.0375, 0,0.01};
Point(50) = {0.123281,-0.03954, 0,0.01};
Point(51) = {0.149805,-0.04101, 0,0.01};
Point(52) = {0.178401,-0.04193, 0,0.01};
Point(53) = {0.208902,-0.04234, 0,0.01};
Point(54) = {0.241131,-0.04229, 0,0.01};
Point(55) = {0.274904,-0.04182, 0,0.01};
Point(56) = {0.310028,-0.04101, 0,0.01};
Point(57) = {0.346303,-0.03992, 0,0.01};
Point(58) = {0.383522,-0.03861, 0,0.01};
Point(59) = {0.421645,-0.03713, 0,0.01};
Point(60) = {0.460398,-0.03538, 0,0.01};
Point(61) = {0.499413,-0.03341, 0,0.01};
Point(62) = {0.538453,-0.03126, 0,0.01};
Point(63) = {0.577282,-0.02899, 0,0.01};
Point(64) = {0.615662,-0.02665, 0,0.01};
Point(65) = {0.653358,-0.02426, 0,0.01};
Point(66) = {0.690139,-0.02188, 0,0.01};
Point(67) = {0.725775,-0.01952, 0,0.01};
Point(68) = {0.760046,-0.01722, 0,0.01};
Point(69) = {0.792738,-0.01499, 0,0.01};
Point(70) = {0.823646,-0.01286, 0,0.01};
Point(71) = {0.852575,-0.01084, 0,0.01};
Point(72) = {0.879342,-0.00894, 0,0.01};
Point(73) = {0.903777,-0.00719, 0,0.01};
Point(74) = {0.925723,-0.00559, 0,0.01};
Point(75) = {0.94504,-0.00416, 0,0.01};
Point(76) = {0.961603,-0.00293, 0,0.01};
Point(77) = {0.975305,-0.00189, 0,0.01};
Point(78) = {0.986056,-0.00107, 0,0.01};
Point(79) = {0.993785,-0.00048, 0,0.01};
Point(80) = {0.998444,-0.00012, 0,0.01};

Spline(1000) = {1:80,1};

Curve Loop(1) = {1000};

Point(100) = {-4,4,0,0.2};
Point(101) = {4,4,0,0.2};
Point(102) = {4,-4,0,0.2};
Point(103) = {-4,-4,0,0.2};
Line(1) = {100,101};
Line(2) = {101,102};
Line(3) = {102,103};
Line(4) = {103,100};
Curve Loop(2) = {1, 2, 3, 4};

Plane Surface(1) = {2, 1};
Extrude{0, 0, 1} {
  Surface{1};
  Layers{1};
  Recombine;
}