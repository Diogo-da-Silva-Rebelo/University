%%fminsearch para metodo de Nelder-Mead
format short;
%[x,fval,exitflag,output]=fminsearch(@NM1,[1,1]) % sem opçoes

%op=optimset('Display','iter');
%[x,fval,exitflag,output]=fminunc(@NM1,[1,0],op) %mostrar em cada iteração 

%op=optimset('PlotFcns',@optimplotfval);
%[x,fval,exitflag,output]=fminunc(@NM1,[1,0],op) %graficamente os valores da funçao objetivo 

%op=optimset('Display','iter','PlotFcns',@optimplotfval);
%[x,fval,exitflag,output]=fminsearch(@NM1,[1,1],op) %ambos em cada iteraçao
%e graficamente

op=optimset('TolX',10e-1);
[x,fval,exitflag,output]=fminsearch(@NM1,[5;2],op) %tolX

%op=optimset('TolFun',1e-12);
%[x,fval,exitflag,output]=fminsearch(@NM1,[1,1],op) %tol fun

%op=optimset('MaxIter',20);
%[x,fval,exitflag,output]=fminsearch(@NM1,[1,1],op) %20 iteraçoes no maximo

%op=optimset('TolX',1e-3,'TolFun',1e-2,'MaxIte',50);
%[x,fval,exitflag,output]=fminsearch(@NM1,[1,1],op)




function [ f ] = NM1( x )
f = abs( (-2)*(x(1)^3) + x(2) ) + x(1) * x(2)
%f = max( x(2) - 1 , cos(x(1)) ) + sin( x(1)^(2) - x(2) )
%f=max(5*x(1) - 10,cos(-x(2)) + abs(x(1)-x(2)));
end