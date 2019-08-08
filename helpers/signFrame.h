
/* Draw into this object. You can either draw into a pixmap or set the array values directly
 */

class signFrame
{
public:
    signFrame(/* args */);
    ~signFrame();

    void convertImageToByteArray();

private:
    QImage image;
    char led[1000];
};

