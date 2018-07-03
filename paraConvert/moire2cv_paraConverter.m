%---------------------------------------------------------------------
%% Convert 31415926535A.txt to 15084536.yaml
% Hanh Le. Last eddited: 7/3/2018
%---------------------------------------------------------------------
format long;
addpath('C:\Users\Photonics\OneDrive\Research\Surgical navigation\3d_Structured_Illumination\3D_less fringe\7_2_2018_rectifyNIR3D\savePara');

A = importdata('31415926535A_2018_7_2.txt');
width = 692;
height = 516;
camera_name = 0;
rows1 = 3;
cols1 = 3;
data1 = [A(1); A(3); A(4); 0; A(2); A(5); 0; 0; 1];

% Write yaml file
fid = fopen('15084536_test.yaml','wt');
fprintf(fid, 'image_width: %d\n',width);
fprintf(fid, 'image_height: %d\n',height);
fprintf(fid, 'camera_name: %d\n',camera_name);

fprintf(fid, 'camera_matrix:\n');
fprintf(fid, ' rows: %d\n',rows1);
fprintf(fid, ' cols: %d\n',cols1);
fprintf(fid, ' data: [ %1.16e, %1.16e, %1.16e, %d, %1.16e, %1.16e, %d, %d, %d ]\n',data1);

distortion_model = 'see_scope';
rows2 = 1;
cols2 = 13;
data2 = A(6:18);

fprintf(fid, 'distortion_coefficients:\n');
fprintf(fid, ' rows: %d\n',rows2);
fprintf(fid, ' cols: %d\n',cols2);
fprintf(fid, ' data: [ %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e,%1.16e, %1.16e, %1.16e ]\n',data2);

data3 = A(19:27);

fprintf(fid, 'rectification_matrix:\n');
fprintf(fid, ' rows: %d\n',rows1);
fprintf(fid, ' cols: %d\n',cols1);
fprintf(fid, ' data: [ %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e ]\n',data3);

rows4 = 3;
cols4 = 4;
data4 = [A(19:21), A(28), A(22:24), A(29), A(25:27) ,A(30)];

fprintf(fid, 'projection_matrix:\n');
fprintf(fid, ' rows: %d\n',rows4);
fprintf(fid, ' cols: %d\n',cols4);
fprintf(fid, ' data: [ %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e,%1.16e, %1.16e ]\n',data4);

fclose(fid);
