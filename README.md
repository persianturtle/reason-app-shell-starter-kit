# What's New?

- upgraded to use the Hooks API

# CSS Flavors

- [styled-components](https://github.com/persianturtle/reason-app-shell-starter-kit)
- [bs-css](https://github.com/persianturtle/reason-app-shell-starter-kit/tree/bs-css)
- [Sass](https://github.com/persianturtle/reason-app-shell-starter-kit/tree/sass)

# Description

This project exists to provide a simple example to help you get started building your [ReasonReact](https://reasonml.github.io/reason-react/) web application. It's purposely kept small and simple to be easy to follow and change as needed.

## Getting Started

```sh
npm install
npm start
```

This will start both `bsb` and `webpack-dev-server` (via the cross platform `npm-run-all`).

## Demo

![Demo](https://github.com/persianturtle/reason-app-shell-starter-kit/raw/master/demo.gif?raw=true)

## Tutorial

[Building an App Shell](https://itnext.io/a-reasonml-tutorial-building-an-app-shell-dd7cc617d0c5) (warning: this is somewhat out of date)

## Motivation

In my journey to Reason, I was searching for an example ReasonReact web app that demonstrated how to set up things like routing and bsb/webpack configurations. I couldn't find any and decided to share this to help others on their journey.

## What's Inside

- Routing via ReasonReact's Router (and thanks to [@thangngoc89](https://github.com/thangngoc89) for his excellent [gist example](https://gist.github.com/thangngoc89/c9162c0263df5427fe9a36fc7f94ac94))
- Route transitions (via bindings to [ReactTransitionGroup](https://github.com/reactjs/react-transition-group))
- A navigation drawer that, when open, responds to touch&mdash;so you're free to use swiping gestures in your app
- Simple, cross platform `bsb` & `webpack` configurations
- [workbox](https://developers.google.com/web/tools/workbox/) for service worker generation
- Multiple flavors of CSS depending (currently [styled-components](https://github.com/persianturtle/reason-app-shell-starter-kit), [bs-css](https://github.com/persianturtle/reason-app-shell-starter-kit/tree/bs-css), and [Sass](https://github.com/persianturtle/reason-app-shell-starter-kit/tree/sass))

## UI Inspiration

- [Flow Dashboard](https://flowdash.co/)
- [Angular Material](https://material.angular.io/components/categories)
