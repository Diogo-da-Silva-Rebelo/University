%%fminunc metodo quasi-Newton ou o metodo ’trust-region
%por defeito usa o quasi-Newton e o BFGS
format short;
%[x,fval,exitflag,output]=fminunc(@QN,[5,5]) %sem opçoes

%op=optimset('Display','iter')
%[x,fval,exitflag,output]=fminunc(@QN,[1,0],op) %display

%op=optimset('PlotFcns',@optimplotfval);
%[x,fval,exitflag,output]=fminunc(@QN,[1,0],op) %graficamente

%op=optimset('TolX',1e-10,'TolFun',1e-12);
%[x,fval,exitflag,output]=fminunc(@QN,[1,0],op) %tolx e tolfun

op=optimset('hessupdate','dfp','TolX',1e-2)
[x,fval,exitflag,output]=fminunc(@QN,[0,0],op) %DFP

%op=optimset($MaxIter%,20);
%[x,fval,exitflag,output]=fminunc(@QN,[1,0],op) %iteraçoes 20 maximo

%op=optimset('tolx',1e-2);
%[x,fval,exitflag,output]=fminunc(@QN,[0,0],op) %tolx e BFGS


function [ f ] = QN( x )
f = 4 * x(1)^3 + 3 * x(2)^4 + 2 * x(2)^2 + x(1) * x(2) - 3 * x(1) - 2 * x(2)
%f=sin(x(1) + x(2)) + ( (x(1) - x(2))^2) - 1.5*x(1) + 2.5*x(2) + 1;
end