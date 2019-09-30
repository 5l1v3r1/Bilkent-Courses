function CA2_code

    clc;
    close all;
    
    %ask for user input Ts
    askTs = 'What is the value of Ts?: ';
    Ts = input(askTs);

    Ts = 0.08325;
    
    studentID = [0, 2, -1, 0, 4, 0, 0, 0, -1, 9, 6, 0];

    popup = uicontrol('Style', 'popup',...
           'String', {'square','triangular','parabolic','truncated ideal', 'double sided'},...
           'Position', [10 340 100 10],... %margin-left, margin-bottom, width, ??
           'Callback', @setmap);
    
    doubleSided = @(n) 10 * exp(-0.25*abs(n));
    
    function setmap(source, event)
        
        val = source.Value;
        
        calcArray = [];
        for t = 0.0 : 0.001 : 0.999
            for n = 1 : 12
             %Step by increments of 0.001, start from 0.0, end at 1
                
                switch val
                    case 1
                        calcArray = [calcArray, doubleSided(n) * squareFunction(Ts, t-n*Ts)];
                    case 2
                        calcArray = [calcArray, doubleSided(n) * triangleFunction(Ts, t-n*Ts)];
                    case 3
                        calcArray = [calcArray, doubleSided(n) * parabolicFunction(Ts, t-n*Ts)];
                    case 4
                        calcArray = [calcArray, doubleSided(n) * truncatedFunction(Ts, t-n*Ts)];
                    case 5
                        calcArray = [calcArray, doubleSided(n) * truncatedFunction(Ts, t-n*Ts)];
                end
           
            end
        end
        legendStudentID = [];
        for n = 1 : 12000
            legendStudentID = [0, legendStudentID];
        end
        for n = 1 : 12
            legendStudentID(n * 1000) = studentID(n);
        end
        dtx = 1:12000;
        hold off;
        plot(dtx ,calcArray, 'color', [0.066, 0.474, 0.654], 'LineWidth', 3); hold on;
        atx = 1:12000;
        stem(atx, legendStudentID, 'color', 'g');
        legend('reconstructed signal','discrete-time sequence')
    end
    
    function squarepT = squareFunction(Ts, t)
        if (-Ts/2) <= t && t <= (Ts/2)
            squarepT = 1;
        else
            squarepT = 0;
        end
    end

    function triangularpT = triangleFunction(Ts, t)
        if -Ts <= t && t <= Ts
            triangularpT = 1 - (abs(t)/Ts);
        else
            triangularpT = 0;
        end
    end

    function parabolicpT = parabolicFunction(Ts, t)
        if -2*Ts <= t && t <= 2*Ts
            parabolicpT = (2 - 2*cos(t))/(Ts*Ts);
        else
            parabolicpT = 0;
        end
    end

    function truncatedpT = truncatedFunction(Ts, t)
       if (-Ts*5) <= t && t <= (Ts*5) %change 3 with 5 for part C
            truncatedpT = sin((pi/Ts)*t)/((pi/Ts)*t);
        else
            truncatedpT = 0;
        end 
    end 
end