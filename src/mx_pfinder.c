#include "../inc/path.h"

void mx_pfinder(int island_count, char **island_names, int starter, int **matrix) {
    int visited[island_count];
    int min_distances[island_count];

    for (int i = 0; i < island_count; i++) {
        visited[i] = 0;
        min_distances[i] = 2147483647;
    }

    min_distances[starter] = 0;

    while(true) {
        int current_id = 2147483647;

        for (int i = 0; i < island_count; i++) {
            if((visited[i] == 0) && (min_distances[i] < 2147483647)) {
                current_id = i;
                break;
            }
        }

        if (current_id < 2147483647) {
            for(int j = 0; j < island_count; j++) {
                if (matrix[current_id][j] > 0) {
                    int temp = min_distances[current_id] + matrix[current_id][j];
                    if(min_distances[j] > temp) {
                        min_distances[j] = temp;
                        visited[j] = 0;
                    }
                }
            }
            visited[current_id] = 1;
        }
        else {
            break;
        }
    }

    for (int i = starter + 1; i < island_count; i++) {
        if (i == starter) {
            continue;
        }

        int number_paths = 0;

        t_path **path_arr = (t_path **)malloc(sizeof(t_path *) * island_count * island_count);
        for (int x = 0; x < island_count * island_count; x++) {
            path_arr[x] = NULL;
            /*path_arr[x]->reverse_path = (int *)malloc(sizeof(int) * island_count);
            path_arr[x]->reverse_distance = (int *)malloc(sizeof(int) * island_count);
            path_arr[x]->reverse_counter = 0;
            path_arr[x]->current_id = i;*/
        }
        path_arr[number_paths] = (t_path *)malloc(sizeof(t_path));
        path_arr[number_paths]->reverse_path = (int *)malloc(sizeof(int) * island_count);
        path_arr[number_paths]->reverse_distance = (int *)malloc(sizeof(int) * island_count);
        path_arr[number_paths]->reverse_counter = 0;
        path_arr[number_paths]->current_id = i;

        

        for (int p = 0; p <= number_paths; p++) {
            int current = path_arr[p]->current_id;

            while (current != starter) {
                int temp = -1;

            //printf("\n\n%d%s\n",starter, island_names[starter]);
                for (int j = 0; j < island_count; j++) {
                    if (matrix[current][j] > 0 &&
                    min_distances[current] - matrix[current][j] == min_distances[j]) {
                    /*
                    sleep(1);
                    printf("%d%s - %d(%s to %s) = %d%s\n",min_distances[current], island_names[current], matrix[current][j],island_names[current],island_names[j],min_distances[j], island_names[j]);
                    */
                        if (temp < 0) {
                            temp = j;
                        
                        }
                        else {
                            number_paths++;
                            mx_path_split(path_arr, number_paths, island_count, j, p);
                            path_arr[number_paths]->reverse_path[path_arr[number_paths]->reverse_counter] = current;
                            path_arr[number_paths]->reverse_distance[path_arr[number_paths]->reverse_counter] = matrix[current][j];
                            path_arr[number_paths]->reverse_counter++;
                        }
                    }
                }

                if(temp >= 0) {
                    path_arr[p]->reverse_path[path_arr[p]->reverse_counter] = current;
                    path_arr[p]->reverse_distance[path_arr[p]->reverse_counter] = matrix[current][temp];
                    path_arr[p]->reverse_counter++;
                    current = temp;
                }
            }

            /////
            mx_printstr("========================================\n");
            /////
            mx_printstr("Path : ");
            mx_printstr(island_names[starter]);
            mx_printstr(" -> ");
            mx_printstr(island_names[i]);
            /////
            mx_printstr("\nRoute : ");
            mx_printstr(island_names[starter]);
            mx_printstr(" -> ");
            for (int j = path_arr[p]->reverse_counter - 1; j >= 0; j--) {
                mx_printstr(island_names[path_arr[p]->reverse_path[j]]);
                if(j > 0) {
                    mx_printstr(" -> ");
                }
            }
            //////
            mx_printstr("\nDistance : ");
            if(min_distances[i] == matrix[starter][i]
            && path_arr[p]->reverse_counter <= 1) {
                mx_printint(matrix[starter][i]);
            }
            else {
                int dist = 0;
                for (int j = path_arr[p]->reverse_counter - 1; j >= 0; j--) {
                    mx_printint(path_arr[p]->reverse_distance[j]);
                    dist += path_arr[p]->reverse_distance[j];
                    if(j > 0) {
                        mx_printstr(" + ");
                    }
                }
                mx_printstr(" = ");
                mx_printint(dist);
            }
                //////
            mx_printstr("\n========================================\n");
            /////
        }

        mx_free_path(&path_arr, island_count);
    }
}
