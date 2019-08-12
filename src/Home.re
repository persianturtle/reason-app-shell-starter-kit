let html = {|
  <h1>Now upgraded to use the Hooks API!</h1>
  <h1>ReasonReact App Shell Boilerplate</h1>
  <p>A simple example to help you get started building your <a href="https://reasonml.github.io/reason-react/">ReasonReact</a> web application. It's purposely kept small and simple to be easy to follow and change as needed.</p>
  <h2>Getting Started</h2>
  <pre><code class="sh language-sh">npm install
  npm start
  </code></pre>
  <p>This will start both <code>bsb</code> and <code>webpack-dev-server</code> (via the cross platform <code>npm-run-all</code>).</p>
  <h2>Demo</h2>
  <p><img src="/demo.gif?raw=true" alt="Demo" /></p>
  <h2>Tutorial</h2>
  <p><a href="https://itnext.io/a-reasonml-tutorial-building-an-app-shell-dd7cc617d0c5">Building an App Shell</a></p>
  <h2>Motivation</h2>
  <p>In my journey to Reason, I was searching for an example ReasonReact web app that demonstrated how to set up things like routing and bsb/webpack configurations. I couldn't find any and decided to share this to help others on their journey.</p>
  <h2>What's Inside</h2>
  <ul>
    <li>Routing (thanks to <a href="https://github.com/thangngoc89">@thangngoc89</a> for his excellent <a href="https://gist.github.com/thangngoc89/c9162c0263df5427fe9a36fc7f94ac94">gist example</a>)</li>
    <li>Route transitions (via bindings to <a href="https://github.com/reactjs/react-transition-group">ReactTransitionGroup</a>)</li>
    <li>A navigation that, when open, responds to touch&mdash;so you're free to use swiping gestures in your app</li>
    <li>Simple, cross platform <code>bsb</code> &amp; <code>webpack</code> configurations</li>
    <li><a href="https://developers.google.com/web/tools/workbox/"><code>workbox</code></a> for service worker generation</li>
    <li>SASS</li>
  </ul>
  <h2>UI Inspiration</h2>
  <ul>
    <li><a href="https://flowdash.co/">Flow Dashboard</a></li>
    <li><a href="https://material.angular.io/components/categories">Angular Material</a></li>
  </ul>
  <h2>Build for Production</h2>
  <pre><code class="sh language-sh">npm run build
  </code></pre>
|};

[@react.component]
let make = () => {
  <div className="Home" dangerouslySetInnerHTML={"__html": html} />;
};