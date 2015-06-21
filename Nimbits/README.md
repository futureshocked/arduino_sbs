IMPORTANT PLEASE READ BEFORE WATCHING THIS LECTURE:

Nimbits has release a new version of their API which has rendered part of this lecture out of date. 

I have updated the sketch so that it works with the new version, however the video is slightly out of date. I will update the video ASAP. In the mean time, you can use the current version of the sketch since it works fine.

Biggest change between what you see in the video and how Nimbits works now is that you cannot post to multiple datapoints in a single request. For example, if you want to store a temperature and humidity reading (i.e. 2 values) you will now have to do one of the following:

1. Do 2 seperate HTTP requests in order to update two datapoints.
2. Do a single HTTP request and store the two values as JSON, OR comma-delimited values OR XML inside the "dx" variable.

An updated video lecture is coming soon. If you have questions, please email me at peter@txplore.com



