
```matlab
X_data = X - 120;
Y_data = Y;

X_rad = X_data *(pi/180);
Y_rad = Y_data *(pi/180);

dist_new = distance1 .* sin(Y_rad);
X_new = cos(X_rad);
Y_new = -cos(Y_rad);
dist_no_back = dist_new <= 40;

figure()
scatter(X_new, Y_new,[], dist_new, 'filled')
colorbar;
xlabel("X distance");
ylabel("Y distance");
zlabel("distance");
axis equal;
```

![figure_0.png](./PIE_sensor_plotting_media/figure_0.png)

```matlab

figure()
scatter(X_new, Y_new,[], dist_no_back, 'filled')
colorbar;
xlabel("X distance");
ylabel("Y distance");
zlabel("distance");
axis equal;
```

![figure_1.png](./PIE_sensor_plotting_media/figure_1.png)
