function KamadaKawai(vertexFile, edgeFile)
% Read data of points into matrix "coordinates"
    coordinates = readmatrix(vertexFile)';
% Get matrix metadata
    [rows, columns, slices] = size(coordinates);
    
% Calculate matrix properties 
    points = coordinates(1, 1);
    coordinates(:,1) = [];   
    states = (columns - 1) / points;
   
% Create a new 3-dimensional matrix representing STATE,POINTS and TIME
    coordinates = reshape(coordinates, 2, points, states);

% Read data of edges into matrix "edges"
    edges = readmatrix(edgeFile);

% Define graph G: 
% frst parameter is source nodes array 
% scnd parameter is target nodes array
    G = graph(edges(:,1), edges(:,2));

    figure;
        
    plot(G, 'XData', coordinates(1,:,1)', 'YData', coordinates(2,:,1)', 'NodeLabel', {}, 'MarkerSize', 7, 'LineWidth', 2, 'NodeColor', 'r', 'EdgeColor', 'k');
    % g = plot(G, 'XData', coordinates(1,:,1)', 'YData', coordinates(2,:,1)', 'NodeLabel', {}, 'MarkerSize', 7, 'LineWidth', 2, 'NodeColor', 'r', 'EdgeColor', 'k');
    % g = plot(G, 'XData', [1, 2, 3, 4, 5, 3], 'YData', [5, 4, 3, 2, 1, 3], 'NodeLabel', {}, 'MarkerSize', 7, 'LineWidth', 2, 'NodeColor', 'r', 'EdgeColor', 'k');

    axis equal;
    grid on;
    title('Kamada-Kawai Algorithm');
    xlabel('X Coordinate');
    ylabel('Y Coordinate');

    drawnow;
    for step = 1:states
        disp(step);
    end
end