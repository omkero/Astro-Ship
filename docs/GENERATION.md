# if you want basic number generator beween two range or value use the basic random library from c++ std
    #include <random>

    int starsCount = 100;
    RectangleShape star;

    std::random_device seeder;
    std::mt19937 engine(1);
    std::uniform_int_distribution<int> dist_x(0, window_width);  // uniform, unbiased
    std::uniform_int_distribution<int> dist_y(0, window_height); // uniform, unbiased

    int star_x = dist_x(engine);
    int star_y = dist_y(engine);

        for (int i = 0; i < starsCount; i++)
    {
        if (i == starsCount)
        {
            return;
        }
        int star_x = dist_x(engine);
        int star_y = dist_y(engine);

        star.Draw(star_x, star_y, 1, 1, color);
    }
    
# here example of generating random stars based on the window height and width 
# be careful of std::mt19937 engine(1); if you use std::mt19937 engine(seeder()); it will keep generating more and more
# std::mt19937 engine(1) is only once you can customize if by your self like add timer etc..