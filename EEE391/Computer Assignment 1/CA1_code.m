clc;
close all;

%ask for user input
askwo = 'What is the value of wo?: ';
wo = input(askwo);

askA1 = 'What is the value of A1?: ';
a1 = input(askA1);

askA2 = 'What is the value of A2?: ';
a2 = input(askA2);

askA3 = 'What is the value of A3?: ';
a3 = input(askA3);

askfi1 = 'What is the value of o1?: ';
fi1 = input(askfi1);

askfi2 = 'What is the value of o2?: ';
fi2 = input(askfi2);

askfi3 = 'What is the value of o3?: ';
fi3 = input(askfi3);

% Define three complex numbers using the inputs
ph1 = a1*exp(1i*degtorad(fi1));
ph2 = a2*exp(1i*degtorad(fi2));
ph3 = a3*exp(1i*degtorad(fi3));

%do the phasor addition
ph = ph1 + ph2 + ph3;

% Step-wise vector sum
vecs = cumsum([ph1; ph2; ph3]);
vec2 = cumsum([0, ph]);
disp(ph);

%check the sign of the phase
ispositive = atan(real(ph)) > 0;

sign = '-';
if ispositive
            sign = '+';
end

finishedResult = sprintf('x(t) = %.2fcos(%dt %s %.2fpi)', abs(ph), wo, sign, (atan(real(ph))));

disp(finishedResult);

% Plot 3 signals and the resulting signal
vecs = [0; vecs]; % add origin as starting point for the resulting signal
figure;
plot(real(vecs), imag(vecs), real(vec2), imag(vec2), '-+');
xlim([-30 30]);
ylim([-30 30]);
xlabel('real part');
ylabel('imaginary part');
grid on;

% Plot
figure;
plot(real(vec2), imag(vec2), 'b','LineWidth',2);
xlim([-30 30]);
ylim([-30 30]);
xlabel('real part');
ylabel('imaginary part');
grid on;
