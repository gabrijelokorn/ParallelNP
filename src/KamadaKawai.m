function KamadaKawai(VertexFile) 
    
    coordinates = readmatrix(% Define the vertices' coordinates
coordinates = [1 1; 2 2; 3 1; 4 3]; % Each row is a vertex with (x, y) coordinates

% Define the edges between vertices
edges = [1 2; 2 3; 3 4; 4 1]; % Each row represents an edge between two vertices

% Create the graph
G = graph(edges(:,1), edges(:,2));

% Initial plot of the graph
figure;
h = plot(G, 'XData', coordinates(:,1), 'YData', coordinates(:,2), ...
     'NodeLabel', {}, 'MarkerSize', 7, 'LineWidth', 2, 'NodeColor', 'r', 'EdgeColor', 'k');
axis equal;
grid on;
title('Animated Node Movement');
xlabel('X Coordinate');
ylabel('Y Coordinate');

% Animation settings
startPos = ([1, 1; 2, 2])
endPos = ([5, 5; 9, 1]);             % New desired position
steps = 100;
x = linspace(startPos(1), endPos(1), steps);
y = linspace(startPos(2), endPos(2), steps);
w = linspace(1, 9, steps);
z = linspace(1, 1, steps);

% Animate the node moving from startPos to endPos
for k = 1:steps
    h.XData(1) = x(k); % Update x position of the first node
    h.YData(1) = y(k); % Update y position of the first node
    h.XData(2) = w(k); % Update x position of the second node
    h.YData(2) = z(k); % Update y position of the second node
    drawnow;
    pause(0.05); % Pause for visibility
end
);
    fprintf("coords: %s\n", coordinates);

end