export default {
    name: 'GstdControl',
    components: {},
    data: function() {
        return {
            count: 0,
            address: '',
            port: 0
        }

    },
    methods: {
        connect() {
            this.$datas.gstc = new GstdClient("http://" + this.address, this.port);
        }
    },
    props: ['name'],
    template: `
<div>
<div style="display:ruby;padding-right: 20px;height: 40px;">
<b-form-group label-size="md" label-cols-sm="3" label="Address" label-align-lg="right" label-for="nested-street">
    <b-form-input  v-model="address" id="nested-street" size="md"></b-form-input>
</b-form-group>

<b-form-group label-size="md" label-cols-sm="3" label="Port" label-align-lg="right" label-for="nested-street" style="padding-right: 25px">
    <b-form-input  v-model="port" id="nested-street" size="md"></b-form-input>
</b-form-group>
<b-button  v-on:click="connect()">
    Configure
</b-button>
</div>
</div>
  `,
};