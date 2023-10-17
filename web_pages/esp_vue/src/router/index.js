import { createRouter, createWebHistory } from 'vue-router'
import HomeView from '../views/HomeView.vue'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'home',
      component: HomeView
    },
    {
      path: '/leds',
      name: 'leds',
      // route level code-splitting
      // this generates a separate chunk (About.[hash].js) for this route
      // which is lazy-loaded when the route is visited.
      component: () => import('../views/LedView.vue')
    },
    {
      path: '/available-WiFi',
      name: 'WiFi',
      component: () => import ('../views/WiFi.vue')
    }
  ]
})

export default router
