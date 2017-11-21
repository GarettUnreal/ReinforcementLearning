function result = animateStateTransition( filename, increment )
  
    data = dlmread(filename, ' ', 0, 0 );
    
    numStates = length(data(:,1));
    
    #figure;
    x = -1.2:0.1:0.6;
    offset = 1.2;
    factor = ( 2 * pi - offset ) / (0.6 + 1.2);
    xprime = (x + 1.2) * factor + offset;
    
    #line( 'XData', x, 'YData', cos(xprime));
    #pointHandle = scatter( 0.5, cos(0.5 + 1.2) * factor + offset );
    #axis([-1.3 0.7 -1.1 1.1]);
    #plot(x, cos(xprime));
    #hold on;
    
    for index=1:increment:numStates
        theta = (data(index,1) + 1.2) * factor + offset;
      #  pointHandle.XData = data(index,1);
       # pointHandle.YData = theta;
        plot(x, cos(xprime), 'g', [data(index,1)], [cos(theta)], 'bo' );
        axis([-1.3 0.7 -1.1 1.1]);
        #plot([data(index,1)], [cos(theta)], 'bo' );
        #axis([-1.3 0.7 -1.1 1.1]);
        
        # pause(.1);
        drawnow;
    endfor
  
