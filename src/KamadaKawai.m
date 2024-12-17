function KamadaKawai(pointsFile, vertexFile, edgeFile, productionFile)

%%% %%% READ FILES %%% %%%
% Read number of points 
    points = readmatrix(pointsFile);
% Points shall be number not array
    points = points(1);

% Read data of points into matrix "coordinates"
    coordinates = readmatrix(vertexFile)';
% Get matrix metadata
    [columns, rows] = size(coordinates);
    
% Calculate matrix properties 
    states = rows / points;
   
% Create a new 3-dimensional matrix representing STATE, POINTS and TIME
    coordinates = reshape(coordinates, columns, points, states);

% Read data of edges into matrix "edges"
    edges = readmatrix(edgeFile);

%Prepare figure
    figure;

% Define graph G: 
% frst parameter is source nodes array 
% scnd parameter is target nodes array
    G = graph(edges(:,1), edges(:,2));
    g = plot(G, 'XData', coordinates(1,:,1)', 'YData', coordinates(2,:,1)', 'NodeLabel', {}, 'MarkerSize', 7, 'LineWidth', 2, 'NodeColor', 'r', 'EdgeColor', 'k');

% Set view of a graph
    axis equal;
    grid on;
    title('Kamada-Kawai Algorithm');
    xlabel('X Coordinate');
    ylabel('Y Coordinate');
    drawnow;
    
% Configuration for animation
    steps = 100;
    fps = 50;
    animationPause = 0.0001;

% Setup the videomaker     
    write = VideoWriter(productionFile);
    write.FrameRate = fps;
    write.Quality = 100;

    open(write);

% Execute the loop
    M = zeros(points, 2, steps);
    for state = 1 : (states - 1) % -1 because we are going to interpolate between states
        for p = 1 : points
            M(p, 1, :) = linspace(coordinates(1,p,state), coordinates(1,p,state + 1), steps);
            M(p, 2, :) = linspace(coordinates(2,p,state), coordinates(2,p,state + 1), steps);
        end

        for s = 1 : steps
            for p = 1 : points
                g.XData(p) = M(p, 1, s);
                g.YData(p) = M(p, 2, s);
            end
            % Draw in figure
            drawnow;
            % Wait a bit
            pause(animationPause);

            frame = getframe(gcf);
            writeVideo(write, frame);
        end
    end

% Finish the animation
    close(write);
end