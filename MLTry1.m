clear all

data18=load('C:\Users\GAURAV PATIL\Desktop\Orangewood\VibrationProfiling\Data\TestML1800.csv');
data17=load('C:\Users\GAURAV PATIL\Desktop\Orangewood\VibrationProfiling\Data\TestML1700.csv');
data16=load('C:\Users\GAURAV PATIL\Desktop\Orangewood\VibrationProfiling\Data\TestML1600.csv');
data15=load('C:\Users\GAURAV PATIL\Desktop\Orangewood\VibrationProfiling\Data\TestML1500.csv');
[Tdata18,Pdata18,Vdata18]=thresholding(data18);
[Tdata17,Pdata17,Vdata17]=thresholding(data17);
[Tdata16,Pdata16,Vdata16]=thresholding(data16);
[Tdata15,Pdata15,Vdata15]=thresholding(data15);
Tdata=Tdata18;
Tdata(201:400,1)=Tdata17;
Tdata(401:600,1)=Tdata16;
Tdata(601:800,1)=Tdata15;

Pdata=Pdata18;
Pdata(201:400,1)=Pdata17;
Pdata(401:600,1)=Pdata16;
Pdata(601:800,1)=Pdata15;

Vdata=Vdata18;
Vdata(201:400,1)=Vdata17;
Vdata(401:600,1)=Vdata16;
Vdata(601:800,1)=Vdata15;

Train(:,1)=Vdata;
Train(:,2)=Pdata;
Train(:,3)=Tdata; 
Label=zeros(800,4);
count18=0;
count17=0;
count16=0;
count15=0;


for i=1:200
    if Tdata18(i,1)==0
         Label(i,1)=1;Label(i+200,1)=1;Label(i+400,1)=1;Label(i+600,1)=1;
         count18=count18+1 ;
    elseif Tdata17(i,1)==0
         Label(i,2)=1;Label(i+200,2)=1;Label(i+400,2)=1;Label(i+600,2)=1;
         count17=count17+1 ;
    elseif Tdata16(i,1)==0
         Label(i,3)=1;Label(i+200,3)=1;Label(i+400,3)=1;Label(i+600,3)=1;
         count16=count16+1 ;   
    
    else 
         Label(i,4)=1;Label(i+200,4)=1;Label(i+400,4)=1;Label(i+600,4)=1;
         count15=count15+1 ;
    
    end
end
% for i=1:200
%     if Tdata18(i,1)==0
%          Label(i,1)=1800;Label(i+200,1)=1800;Label(i+400,1)=1800;Label(i+600,1)=1800;
%          count18=count18+1 ;
%     elseif Tdata17(i,1)==0
%          Label(i,2)=1700;Label(i+200,2)=1700;Label(i+400,2)=1700;Label(i+600,2)=1700;
%          count17=count17+1 ;
%     elseif Tdata16(i,1)==0
%          Label(i,3)=1600;Label(i+200,3)=1600;Label(i+400,3)=1600;Label(i+600,3)=1600;
%          count16=count16+1 ;   
%     
%     else 
%          Label(i,4)=1500;Label(i+200,4)=1500;Label(i+400,4)=1500;Label(i+600,4)=1500;
%          count15=count15+1 ;
%     
%     end
% end


for i=1:10
    

end

subplot(4,1,1);
plot(Pdata18,Tdata18,'r');
ylabel('Vib Amp');
xlabel('V=1800 mm/rev');

subplot(4,1,2);
plot(Pdata17,Tdata17,'b');
ylabel('Vib Amp')
xlabel('V=1700 mm/rev');

subplot(4,1,3);
plot(Pdata16,Tdata16,'g');
ylabel('Vib Amp')
xlabel('V=1600 mm/rev');

subplot(4,1,4);
plot(Pdata15,Tdata15,'y');
ylabel('Vib Amp')
xlabel('V=1500 mm/rev');

function [Newdata,datap,datav]=thresholding(data)
n=length(data(:,3)) ;

datav=data(:,1);
datax=data(:,3);
dataz=data(:,4);
% in=.75;
dataZ= sqrt((datax).^2+(dataz).^2);
datap=round((data(:,2))); 
Mean=mean(dataZ);
Std=std(dataZ);
dataZm=max(0,abs(dataZ-Mean)-1.2*Std);
% dataZm(n:n+3)=0;
Newdata=dataZm;
% Newdata(1,1)=0;
% for i=1:n
% %  Newdata(i,1)=dataZm(i+1,1)*in +(1-in)*dataZm(i,1);
%    Newdata(i,1)=mean(dataZm(i:i+2));
% end
end