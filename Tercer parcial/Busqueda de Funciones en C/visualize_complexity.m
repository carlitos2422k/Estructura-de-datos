function visualize_complexity(csv_file)
    % Leer el CSV
    data = readtable(csv_file);
    
    % Crear mapa de complejidades
    complexity_map = containers.Map;
    complexity_map('O(1)') = 1;
    complexity_map('O(n)') = 2;
    complexity_map('O(n^2)') = 3;
    complexity_map('O(n^3)') = 4;
    complexity_map('O(2^n)') = 5;
    
    % Convertir complejidades a valores numéricos
    complexity_values = zeros(height(data), 1);
    for i = 1:height(data)
        complexity = char(data.Complejidad(i));
        if isKey(complexity_map, complexity)
            complexity_values(i) = complexity_map(complexity);
        end
    end
    
    % Crear figura
    figure('Position', [100, 100, 1200, 800]);
    
    % 1. Gráfico de barras
    subplot(2, 1, 1);
    bar(complexity_values);
    title('Complejidad por Función');
    xlabel('Índice de Función');
    ylabel('Nivel de Complejidad');
    xticks(1:length(data.Nombre));
    xticklabels(data.Nombre);
    xtickangle(45);
    grid on;
    
    % 2. Gráfico de pastel
    subplot(2, 1, 2);
    [unique_complexities, ~, ic] = unique(data.Complejidad);
    complexity_counts = accumarray(ic, 1);
    pie(complexity_counts);
    legend(unique_complexities, 'Location', 'eastoutside');
    title('Distribución de Complejidades');
    
    % Guardar figura
    saveas(gcf, 'complexity_analysis_matlab.png');
    
    % Mostrar estadísticas
    fprintf('\nEstadísticas de Complejidad:\n');
    for i = 1:length(unique_complexities)
        fprintf('%s: %d funciones (%.1f%%)\n', ...
            char(unique_complexities(i)), ...
            complexity_counts(i), ...
            (complexity_counts(i)/sum(complexity_counts))*100);
    end
end