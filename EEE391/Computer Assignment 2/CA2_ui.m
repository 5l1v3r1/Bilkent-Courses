function CA2_ui
    % Create a figure and axes
    H = [0, 2, -1, 0, 4, 0, 0, 0, -1, 9, 6, 0];
    dtx = -4:7;
    s = stem(dtx, H);
    
    % Create pop-up menu
    popup = uicontrol('Style', 'popup',...
           'String', {'square','triangular','parabolic','truncated ideal'},...
           'Position', [10 340 100 10],... %margin-left, margin-bottom, width, ??
           'Callback', @setmap);    
  
    % Make figure visble after adding all components
    s.Visible = 'on';
    
    function setmap(source,event)
        val = source.Value;
        maps = source.String;
        % For R2014a and earlier: 
        % val = get(source,'Value');
        % maps = get(source,'String'); 

        newmap = maps{val};
        colormap(newmap);
    end
end